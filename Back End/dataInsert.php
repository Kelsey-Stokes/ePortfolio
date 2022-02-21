<?php
/*
author: Kelsey Stokes
created: 02/11/2022
dataInsert.php
This file connects to hvac database and inserts rows from a csv file   
 */

// Open the .csv file
$file = fopen("data.csv", "r");

// Read file into array
while(! feof($file)) {
    $arr = fgetcsv($file);
}

// Get today's date
$date = date("Y-m-d");

// Open MYSQL credentials file (read-only)
$credentials = fopen("credentials.csv", "r");

// Parse the file
while(! feof($credentials)) {
    $credentialsArr = fgetcsv($credentials);
}

// Copy credentials from array
$servername = $credentialsArr[0];
$database = $credentialsArr[1];
$username = $credentialsArr[2];
$password = $credentialsArr[3];

// Create database connection
$mysqli_connection = new MySQLi($servername, $username, $password, $database);
if ($mysqli_connection->connect_error) {
   echo "Not connected, error: " . $mysqli_connection->connect_error;
}
else {
   echo "Connected.";
}

// Prepare the SQL query
$sql = "INSERT INTO hours (date, ac_hours, heat_hours)
        VALUES ('$date' ,$arr[0], $arr[1])";

// Execute the query
if(!($import = $mysqli_connection->query($sql))) {
     echo "\nQuery execute failed: ERRNO: (" . $mysqli->errno . ") " . $mysqli->error;

}