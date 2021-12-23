<?php

include './connect.php';
$json=array();

$connect = mysqli_connect($hostname, $username, $password, $database);
$query = "select * from dht11 where id= '1' ";
$results = mysqli_query($connect, $query);
    
if($data=mysqli_fetch_array($results)){
    $result["temperature"]=$data['temperature'];
    $result["humidity"]=$data['humidity'];
    $json=$result;
}else{
    $result["temperature"]='0';
    $result["humidity"]='0';
    $json=$result;
}

mysqli_close($connect);
echo json_encode($json);