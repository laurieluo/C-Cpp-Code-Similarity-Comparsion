<?php
exec("cd /home/CodeSimilarity && ./main");
sleep(2);

$file_path = "/home/CodeSimilarity/out/Final.out" ;
if (file_exists($file_path)) {
    $fp = fopen($file_path, "r");
    $str = fread($fp, filesize ( $file_path )); //指定读取大小，这里把整个文件内容读取出来
    echo $str = str_replace("\r\n", "<br />", $str);
}

?>  
