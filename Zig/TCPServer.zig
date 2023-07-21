const std = @import("std");
pub fn main()!void
{
 var buffer:[256]u8 = undefined;
 var server = std.net.StreamServer.init(.{ .reuse_address = true });    //Create server
 try server.listen(std.net.Address.initIp4([4]u8{ 0, 0, 0, 0 }, 3721)); //Listen on address
 while (true)
 {
  var client = try server.accept();                                     //Accept client
  var size = try client.stream.read(&buffer);                           //Read message from client
  std.debug.print("{s}", .{buffer[0..size]});                           //Print message to console
  size = try client.stream.write("Message received\n");                 //Send response
  client.stream.close();                                                //Close connection
 }
}