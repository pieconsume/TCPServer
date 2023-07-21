use IO::Socket::INET;
$buffer="";
while(true)
{
 $message=<STDIN>;              //Read message from stdin
 $client=IO::Socket::INET->new( //Create client with settings
  Proto=>'tcp',
  PeerPort=>3721,
  PeerAddr=>"127.0.0.1");
 $client->send($message);       //Send message to server
 $client->recv($buffer, 0xFF);  //Recieve response from server
 print($buffer);                //Print response to console
 $client->close();              //Close connection
}