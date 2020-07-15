/*
 * @Description: 
 * @Author: Loki Zhao
 * @Copyright: Loki Zhao
 * @Date: 2019-08-29 15:34:20
 * @LastEditors: Loki Zhao
 * @LastEditTime: 2020-07-15 16:20:45
 */
var net = require('net')

var HOST = '10.96.16.30'
var PORT = 3100

let sendData = function () {
    var client = new net.Socket()
    client.connect(PORT, HOST, function () {
        client.write(`hello from client 你好`)
    });

    client.on('data', function (data) {
        //得到返回数据
        console.log('DATA is: ')
        console.log(data.toString('utf8').replace('/^\r/$', ''))
        client.destroy()
    })

    client.on('end', function () {
        console.log('request end')
    })

    client.on('close', function () {
        console.log('Connection closed')
    })

    client.on('error', function (error) {
        console.error(error)
    })
}

// setInterval(sendData,500)
sendData()
