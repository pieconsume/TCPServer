const net=require("net")
//I couldn't figure out how to set address reuse so it isn't done here
const server=net.createServer(client=>
{
 client.on('data',data=>
 {
  process.stdout.write(data.toString('ascii')) //When a message is recieved write it to console
 })
 client.write("Message received\n")            //Send reply
 client.close()                                //Close the client
})
server.listen(3721) //Start listening on port 3721