const std = @import("std");
pub fn main()!void{
 var buffer:[256]u8=undefined;
 var server=std.net.StreamServer.init(.{.reuse_address=true });
 try server.listen(std.net.Address.initIp4([4]u8{0,0,0,0},3721));
 while (true){
  var client=try server.accept();
  var size=try client.stream.read(&buffer);
  std.debug.print("{s}",.{buffer[0..size]});
  size=try client.stream.write("Message received\n");
  client.stream.close();}}