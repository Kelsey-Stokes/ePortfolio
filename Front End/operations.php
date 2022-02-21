<!-- 
author: Kelsey Stokes
created: 02/11/2022


operations.php
All of the algorithmic operations happen here. This includes total hours,
approximate wattage, and estimated costs
-->

<?php

// Get total hours so far this month for both A/C and heat
$acSum = array_sum(array_column($acHours, "y"));
$heatSum = array_sum(array_column($heatHours, "y"));

// TEST PRINTS :: Will Delete
// print "Sum of A/C Array : ".$acSum."<br/>";
// print "Sum of Heat Array : ".$heatSum."<br/>";

// Calculate the wattage
$acKilowatts = $acSum * 3000;
$heatKilowatts = $heatSum * 750;

// TEST PRINTS :: Will Delete
// print "Wattage<br/>";
// print "A/C: ".$acKilowatts."kw<br/>";
// print "Heat: ".$heatKilowatts."kw<br/>";

// Calculate the Cost
$acCost = round(($acSum * 0.43), 2);
$heatCost = round(($heatSum * 0.17), 2);
$totalCost = $acCost + $heatCost;
$costTitle = "title";

// TEST PRINTS :: Will Delete
// print "Cost<br/>";
// print "A/C: $".$acCost."<br/>";
// print "Heat: $".$heatCost."<br/>";



?>