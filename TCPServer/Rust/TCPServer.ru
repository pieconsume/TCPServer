//Includes
 use std::net::{TcpListener, Shutdown};
 use std::io::{Read, Write};
 use std::str;

fn main()
{
 //I don't know if unwrapping every function is a good practice, but I'm unfamiliar with Rust so I'm not sure what I should do instead
 let mut buffer:[u8;256] = [0;256];
 let server = TcpListener::bind("0.0.0.0:3721").unwrap();  //Create server
 //Rust doesn't provide a simple way of setting socket options so it is not set here
 loop
 {
   let(mut client, _address) = server.accept().unwrap();   //Accept client
   let size = client.read(&mut buffer).unwrap();           //Read message from client
   print!("{}", str::from_utf8(&buffer[..size]).unwrap()); //Print message to console
   client.write(b"Message received\n").unwrap();           //Send reply to console
   client.shutdown(Shutdown::Both).unwrap();               //Close connection. I'm not sure if shutdown differs from the close() function in other languages in any way
 }
}