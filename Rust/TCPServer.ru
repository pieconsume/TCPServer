//Includes
 use std::net::TcpListener;
 use std::io::{Read, Write};
 use std::str;
fn main(){
 let mut buffer:[u8;256]=[0;256];
 let server=TcpListener::bind("0.0.0.0:3721").unwrap();
 loop{
   let(mut client,_address)=server.accept().unwrap();
   let size=client.read(&mut buffer).unwrap();
   print!("{}",str::from_utf8(&buffer[..size]).unwrap());
   client.write(b"Message received\n").unwrap();}}