use IO::Socket::INET;
$server=IO::Socket::INET->new(Listen=>5,LocalAddr=>'0.0.0.0',LocalPort=>3721,Proto=>'tcp',ReusePort=>true);
$buffer="";
while(true){
  $client=$server->accept();
  $client->recv($buffer,0xFF);
  print($buffer);
  $client->send("Message received\n");
  $client->close();}