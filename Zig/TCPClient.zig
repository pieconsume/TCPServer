const std = @import("std");
pub fn main()!void{
 const stdin=std.io.getStdIn().reader();
 const address=std.net.Address.initIp4([4]u8{127,0,0,1},3721);
 while(true){
  var buffer:[256]u8=undefined;
  var size=try stdin.read(&buffer);
  var client=try std.net.tcpConnectToAddress(address);
  _=try client.write(buffer[0..size]);
  size=try client.read(&buffer);
  std.debug.print("{s}",.{buffer[0..size]});
  client.close();}}