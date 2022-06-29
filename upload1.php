<?php
    if(!empty($_FILES)){
        $tmpname   = $_FILES['upfile']['tmp_name'];     // 临时文件名称
        $name      = $_FILES['upfile']['name'];         // 文件的原名称
        $path      = '/home/CodeSimilarity/upload';                       // 上传目录
        if(move_uploaded_file($tmpname, $path.'/'.$name)){
            rename("/home/CodeSimilarity/upload/$name", "/home/CodeSimilarity/upload/1.cpp");
            echo "<script>alert('$name Upload Success!')</script>";
        }else{
            echo "<script>alert('$name Upload Failed!')</script>";
        }
    }
?>
