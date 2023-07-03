const net=require("net")
const stdin=process.openStdin()
stdin.addListener("data",message=>{
 const client=new net.Socket()
 client.connect(3721,"127.0.0.1")
 client.write(message)
 client.on('data',data=>{process.stdout.write(data.toString('ascii'))})
 client.close()})