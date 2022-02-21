<!DOCTYPE html>

<!-- 
author: Kelsey Stokes
created: 02/11/2022


index.php
File for graph creation, rendering, and positioning on the page
-->

<html>
<head>
    <title>Home Thermostat Dashboard</title>
    
    <?php
    
    // Include external .php files
    include 'getData.php';      // File for getting the database data
    include 'operations.php';   // Calculates wattage and cost
    
    ?>

    <!--  Script to configure and render the charts -->
    <script>
        window.onload = function () {
        
        // Heat and A/C line chart
        var heat_ac_usage = new CanvasJS.Chart("heat_ac_usage", {
            animationEnabled: true,
            theme: "light2",
            title:{
                text: "Monthly Heat and A/C Usage"
            },
            axisY2: {
                title: "Hours used per day",

            },
            data: [{        
                type: "line",
                axisYType: "secondary",
                name: "A/C",
                // Use data from array 
                dataPoints: <?php echo json_encode($acHours, JSON_NUMERIC_CHECK); ?>
            },
            {
                type: "line",
                axisYType: "secondary",
                name: "Heat",
                // Use data from array
                dataPoints: <?php echo json_encode($heatHours, JSON_NUMERIC_CHECK); ?>
            }
        ]
        });
        heat_ac_usage.render(); 

        // A/C wattage bar graph
        var ac_wattage_chart = new CanvasJS.Chart("ac_watts", {
            animationEnabled: true, 
            theme: "light1", // "light1", "light2", "dark1", "dark2"
            title:{
                text: "Approximate A/C Wattage"
            },
            axisY: {
                title: "kilowatts",
                
                // Set Y axis range 0-500,000
                minimum: 0,
                maximum: 500000
            },
            data: [{        
                type: "column",  
                yValueFormatString: "##0.00 kw", // Format text
                
                // Get A/C wattage calculated by operations.php
                dataPoints: [      
                    { y: <?php echo $acKilowatts; ?>, label: "A/C" }
                ]
            }]
        });
        ac_wattage_chart.render();

        // Overall and seperate costs - pie chart
        var overall_cost_chart = new CanvasJS.Chart("overall_cost", {
            animationEnabled: true,
            title: {
                
                text: "Estimated Cost Breakdown"
                
            },
            data: [{
                type: "pie",
                startAngle: 240,
                yValueFormatString: "$##0.00", // Format hover text
                indexLabel: "{label} {y}",
                
                // Get the costs calculated by operations.php
                dataPoints: [
                    {y: <?php echo $acCost; ?>, label: "A/C"},
                    {y: <?php echo $heatCost; ?>, label: "Heat"}
                ]
            }]
        });
        overall_cost_chart.render();

        // Heat wattage bar graph
        var heat_wattage_chart = new CanvasJS.Chart("heat_watts", {
            animationEnabled: true,
            theme: "light1", // "light1", "light2", "dark1", "dark2"
            title:{
                text: "Approximate Heat Wattage"
            },
            axisY: {
                title: "kilowatts",
                
                // Set the Y axis range 0-50
                minimum: 0,
                maximum: 50000
            },
            data: [{        
                type: "column", 
                yValueFormatString: "##0.00 kw",    // Format hover text
                color: "red",       // Set the bar color for red
                
                // Get heat wattage calculated by operations.php
                dataPoints: [      
                    { y: <?php echo $heatKilowatts; ?>, label: "Heat" }
                ]
            }]
        });
        heat_wattage_chart.render();
        
        }
        </script>
</head>
<body>
    <!-- Heat and A/C usage line chart container -->
    <div id="heat_ac_usage" style="height: 300px; width: 100%;"></div>
    <!-- A/C wattage bar graph container -->
    <div id="ac_watts" style="border: solid rgb(79, 11, 238); float: left; height: 300px; width: 28%; margin: 25px">
    </div>
    <!-- Cost breakdown pie graph container -->
    <div id="overall_cost" style="border: solid rgb(0, 0, 0); float: left; height: 300px; width: 28%; margin: 25px"></div>
    <!-- Heat wattage bar graph container -->
    <div id="heat_watts" style="border: solid rgb(170, 28, 106); float: left; height: 300px; width: 28%; margin: 25px">
    </div>
    <!-- Include canvas.js as source -->
    <script src="https://canvasjs.com/assets/script/canvasjs.min.js"></script>

</script>

</body>
</html>