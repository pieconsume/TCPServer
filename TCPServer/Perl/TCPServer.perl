use IO::Socket::INET;
$server=IO::Socket::INET->new(         #Create server with settings
 Proto=>'tcp',
 LocalPort=>3721,
 LocalAddr=>'0.0.0.0',
 Listen=>5,
 ReuseAddr=>true);
$buffer="";
while(true)
{
  $client=$server->accept();           #Accept client
  $client->recv($buffer,0xFF);         #Recieve message from client
  print($buffer);                      #Print message to console
  $client->send("Message received\n"); #Send response
  $client->close();                    #Close client
}