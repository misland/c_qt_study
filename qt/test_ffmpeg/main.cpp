#include <iostream>
#include <iomanip>
#include <stdio.h>

#define __STDC_CONSTANT_MACROS

using namespace std;
extern "C"
{
#include <libavcodec/avcodec.h>
//#include <libavformat/avformat.h>
//#include <libswscale/swscale.h>
//#include <libavdevice/avdevice.h>
//#include <libavformat/version.h>
//#include <libavutil/time.h>
//#include <libavutil/mathematics.h>
}

#define TEST_H264 0
#define TEST_HEVC 0

int main()
{
    cout << "Hello FFmpeg!" << endl;
    //在4.0版本后，该方法可以忽视，不需要再调用也能正常使用
    //av_register_all();
    //avcodec.dll的版本号
    unsigned version=avcodec_version();
    cout << "avcodec version is:" << showbase << setw(4) << hex << version <<endl;

    //decode
    AVCodec *pCodec;
    AVCodecContext *pCodecCtx=NULL;
    AVCodecParserContext *pCodecParserCtx=NULL;
    FILE *fp_out;
    FILE *fp_in;
    AVFrame *pFrame;
    const int in_buffer_size=4096;
    uint8_t in_buffer[in_buffer_size+AV_INPUT_BUFFER_PADDING_SIZE]={0};
    uint8_t *cur_ptr;
    int cur_size;
    AVPacket packet;
    int ret,got_picture;
    int y_size;

#if TEST_HEVC
    enum AVCodecID codec_id=AV_CODEC_ID_HEVC;
    char filepath_in[]="bigbuckbunny_480x272.hevc";
#elif TEST_H264
    AVCodecID codec_id=AV_CODEC_ID_H264;
    char filepath_in[]="bigbuckbunny_480x272.h264";
#else
    AVCodecID codec_id=AV_CODEC_ID_MPEG2VIDEO;
    char filepath_in[]="bigbuckbunny_480x272.m2v";
#endif

    char filepath_out[]="bigbuckbunny_480x272.yuv";
    int first_time=1;

    pCodec=avcodec_find_decoder(codec_id);
    if(!pCodec)
    {
        printf("Codec not found\n");
        return -1;
    }

    pCodecCtx=avcodec_alloc_context3(pCodec);
    if(!pCodecCtx)
    {
        printf("Could not allocate video codec context \n");
        return -1;
    }

    pCodecParserCtx=av_parser_init(codec_id);
    if(!pCodecParserCtx)
    {
        printf("Could not allocate video parser context \n")    ;
        return -1;
    }

    if(avcodec_open2(pCodecCtx,pCodec,NULL)<0)
    {
        printf("Could not open codec \n");
        return  -1;
    }

    //把文件放到编译文件夹下，而不是Debug或Release文件夹下
    fp_in=fopen(filepath_in,"rb");
    if(!fp_in)
    {
        printf("Could not open input file \n");
        return -1;
    }

    fp_out=fopen(filepath_out,"wb");
    if(!fp_out)
    {
        printf("Could not open output yuv file \n");
        return  -1;
    }

    pFrame =av_frame_alloc();
    av_init_packet(&packet);
    while (1) {
        //先读了4096个字节的数据
        cur_size=fread(in_buffer,1,in_buffer_size,fp_in);
        if(cur_size==0)
        {
            break;
        }
        //输入文件的指针
        cur_ptr=in_buffer;
        while (cur_size>0) {
            //转换packet，如果一个读到的4096字节中有packet，具体可能是每个packet有个固定的开头这种
            //如果有，对应的应该有packet的长度，那就会把这个packet读完，返回值len应该是packet的长度
            //并且把这个长度赋给packet.size
            int len=av_parser_parse2(pCodecParserCtx,pCodecCtx,&packet.data,&packet.size,
                                     cur_ptr,cur_size,
                                     AV_NOPTS_VALUE,
                                     AV_NOPTS_VALUE,
                                     AV_NOPTS_VALUE);
            //文件指针往前移len，移到下个packet的开始处
            cur_ptr+=len;
            cur_size-=len;
            if(packet.size==0)
            {
                continue;
            }
            printf("[Packet]Size:%6d \t",packet.size);
            switch (pCodecParserCtx->pict_type) {
            case AV_PICTURE_TYPE_I:
                printf("Type:I \t");
                break;
            case AV_PICTURE_TYPE_P:
                printf("Type:P\t");
                break;
            case AV_PICTURE_TYPE_B:
                printf("Type:B\t");
                break;
            default:
                printf("Type:Other\t");
                break;
            }
            printf("Number:%4d\n",pCodecParserCtx->output_picture_number);

            //使用新的组合方法可以不用再担心遗留数据问题
            ret=avcodec_send_packet(pCodecCtx,&packet);
            if(ret!=0)
            {
                printf("Decode error\n");
                return  -1;
            }
            if (avcodec_receive_frame(pCodecCtx,pFrame)==0) {
                if(first_time)
                {
                    printf("\nCodec Full Name:%s\n",pCodecCtx->codec->long_name);
                    printf("width:%d\nheight:%d\n",pCodecCtx->width,pCodecCtx->height);
                    first_time=0;
                }
                for (int i=0;i<pFrame->height;i++) {
                    fwrite(pFrame->data[0]+pFrame->linesize[0]*i,1,pFrame->width,fp_out);
                }
                for (int i=0;i<pFrame->height/2;i++) {
                    fwrite(pFrame->data[1]+pFrame->linesize[1]*i,1,pFrame->width/2,fp_out);
                }
                for (int i=0;i<pFrame->height/2;i++) {
                    fwrite(pFrame->data[2]+pFrame->linesize[2]*i,1,pFrame->width/2,fp_out);
                }
                printf("Succeed to decode 1 frame,frame number:%d\n",pCodecCtx->frame_number);
            }
            else {
                printf("Failed to decode packet\n");
            }

            //avcodec_decode_video2方法已过期，不建议使用了
            //ret=avcodec_decode_video2(pCodecCtx,pFrame,&got_picture,&packet);
            //            if(ret<0)
            //            {
            //                printf("Decode error\n");
            //                return  -1;
            //            }
            //            if(got_picture)
            //            {
            //                if(first_time)
            //                {
            //                    printf("\nCodec Full Name:%s\n",pCodecCtx->codec->long_name);
            //                    printf("width:%d\nheight:%d\n",pCodecCtx->width,pCodecCtx->height);
            //                    first_time=0;
            //                }
            //                for (int i=0;i<pFrame->height;i++) {
            //                    fwrite(pFrame->data[0]+pFrame->linesize[0]*i,1,pFrame->width,fp_out);
            //                }
            //                for (int i=0;i<pFrame->height/2;i++) {
            //                    fwrite(pFrame->data[1]+pFrame->linesize[1]*i,1,pFrame->width/2,fp_out);
            //                }
            //                for (int i=0;i<pFrame->height/2;i++) {
            //                    fwrite(pFrame->data[2]+pFrame->linesize[2]*i,1,pFrame->width/2,fp_out);
            //                }
            //                printf("Succeed to decode 1 frame\n");
            //            }

            //如果使用avcodec_decode_video2，会在解析完视频数据后还有部分数据遗留在结构体内，需要清除掉，如下
            //Flush Decoder
            //    packet.data=NULL;
            //    packet.size=0;
            //    while (1) {
            //        ret=avcodec_decode_video2(pCodecCtx,pFrame,&got_picture,&packet);
            //        if(ret<0)
            //        {
            //            printf("Decode Error\n");
            //            return -1;
            //        }
            //        if(got_picture)
            //        {
            //            break;
            //        }
            //        else {
            //            for (int i=0;i<pFrame->height;i++) {
            //                fwrite(pFrame->data[0]+pFrame->linesize[0]*i,1,pFrame->width,fp_out);
            //            }
            //            for (int i=0;i<pFrame->height/2;i++) {
            //                fwrite(pFrame->data[1]+pFrame->linesize[1]*i,1,pFrame->width,fp_out);
            //            }
            //            for (int i=0;i<pFrame->height/2;i++) {
            //                fwrite(pFrame->data[2]+pFrame->linesize[2]*i,1,pFrame->width,fp_out);
            //            }
            //            printf("Flush Decoder:Succeed to decode 1 frame \n");
            //        }
            //    }

        }
    }

    fclose(fp_in);
    fclose(fp_out);
    av_parser_close(pCodecParserCtx);
    av_frame_free(&pFrame);
    avcodec_close(pCodecCtx);
    av_free(pCodecCtx);


    return 0;
}
