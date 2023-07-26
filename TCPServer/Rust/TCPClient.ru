//Includes
 use std::net::{TcpStream, Shutdown};
 use std::io::{Read, Write, stdin};
 use std::str;

fn main()
{
 loop
 {
  //I don't know if unwrapping every function is a good practice, but I'm unfamiliar with Rust so I'm not sure what I should do instead
  let mut buffer:[u8;256] = [0;256];
  let mut size = stdin().read(&mut buffer).unwrap();              //Read message from stdin
  let mut client = TcpStream::connect("127.0.0.1:3721").unwrap(); //Connect to server
  client.write(&buffer[..size]).unwrap();                         //Write message to server
  size = client.read(&mut buffer).unwrap();                       //Read response from server
  print!("{}",str::from_utf8(&buffer[..size]).unwrap());          //Print response to console
  client.shutdown(Shutdown::Both).unwrap();                       //Close connection. I'm not sure if shutdown differs from the close() function in other languages in any wa
 }
}