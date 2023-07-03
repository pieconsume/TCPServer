//Includes
 use std::net::TcpStream;
 use std::io::{Read, Write, stdin};
 use std::str;
fn main(){
 loop{
  let mut buffer:[u8;256]=[0;256];
  let mut size=stdin().read(&mut buffer).unwrap();
  let mut client=TcpStream::connect("127.0.0.1:3721").unwrap();
  client.write(&buffer[..size]).unwrap();
  size=client.read(&mut buffer).unwrap();
  print!("{}",str::from_utf8(&buffer[..size]).unwrap());}}