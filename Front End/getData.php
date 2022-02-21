<!-- 
author: Kelsey Stokes
created: 02/11/2022

getData.php
This file handles connecting to the MYSQL database and running the query
for the data used to render the graphs 
-->

<?php
    
    // Arrays for holding db data
    $acHours = array();
    $heatHours = array();
    

    try{
        // Creating a new connection.
       $link = new \PDO(   'mysql:host=sql647.main-hosting.eu;dbname=u904212892_hvac;charset=utf8mb4',
                           'u904212892_root', 
                           '1~GLS=b5', 
                           array(
                               \PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION,
                               \PDO::ATTR_PERSISTENT => false
                           )
                       );
       
       // Get current mont's A/C data from hours table
       $handle = $link->prepare('select date, ac_hours from hours where 
                        year(date) = year(now()) and month(date) = month(now())');
       $handle->execute(); 
       $result = $handle->fetchAll(\PDO::FETCH_OBJ);
           
       // Add each item to the array
       foreach($result as $row){
           array_push($acHours, array("label"=> $row->date, "y"=> $row->ac_hours));
       }
       
       // Get current month's heat data
       $handle = $link->prepare('select date, heat_hours from hours where 
                        year(date) = year(now()) and month(date) = month(now())'); 
       $handle->execute(); 
       $result = $handle->fetchAll(\PDO::FETCH_OBJ);
           
       // Add heat data to array
       foreach($result as $row){
           array_push($heatHours, array("label"=> $row->date, "y"=> $row->heat_hours));
       }
       
       // Close db connection
       $link = null;
   }
   catch(\PDOException $ex){
       print($ex->getMessage());
   }
    ?>