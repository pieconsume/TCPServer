const net=require("net")
const server=net.createServer(client=>{
 client.on('data',data=>{process.stdout.write(data.toString('ascii'))})
 client.write("Message received\n")
 client.close()})
server.listen(3721)