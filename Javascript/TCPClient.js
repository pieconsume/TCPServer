const net=require("net")
const stdin=process.openStdin()   //Get stdin handle
stdin.addListener("data",message=>
{
 const client=new net.Socket()    //Once something is read from stdin create a new socket
 client.connect(3721,"127.0.0.1") //Connect to server
 client.write(message)            //Write the message to the server
 client.on('data',data=>          //When a reply is recieved write it to stdout
 {
  process.stdout.write(data.toString('ascii'))
 })
 client.close()                   //Close the client
})