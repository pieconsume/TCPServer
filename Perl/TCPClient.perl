use IO::Socket::INET;
$buffer="";
while(true){
 $message=<STDIN>;
 $client=IO::Socket::INET->new(PeerAddr=>"127.0.0.1",PeerPort=>3721,Proto=>'tcp');
 $client->send($message);
 $client->recv($buffer, 0xFF);
 print($buffer);
 $client->close();}