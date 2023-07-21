const std = @import("std");
pub fn main()!void
{
 const stdin = std.io.getStdIn().reader();
 const address = std.net.Address.initIp4([4]u8{ 127, 0, 0, 1 }, 3721);
 var buffer:[256]u8 = undefined;
 while(true){
  var size = try stdin.read(&buffer);                    //Read message from stdin
  var client = try std.net.tcpConnectToAddress(address); //Connect to server
  _ = try client.write(buffer[0..size]);                 //Write message to server
  size = try client.read(&buffer);                       //Read response from server
  std.debug.print("{s}", .{buffer[0..size]});            //Print response to console
  client.close();                                        //Close connection
 }
}