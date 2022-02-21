## About Me

I began my Computer Science program at Southern New Hampshire University with very basic computer skills and absolutely no experience programming. In the past four years I have become proficient in C++, Java, and Python and have familiarized myself with several other languages. I have studied best practices regarding style, performance, and security and have learned how to effectively implement each in my own projects. I was able to learn about version control and team collaboration on GitHub, one of the most commonly used platforms. I practiced mock communications with different roles from the development process such as a project manager, testing, and even end users and stakeholders. 
This ePortfolio demonstrates my ability to develop efficient, error-free code while adhering to standards and honoring best practices. It showcases my ability to select data structures most suitable for a particular situation and to then work with those structures to modify or transmit the data they hold using algorithms. Lastly, it highlights my ability to create databases and work with them on both the client and server side.

## About This ePortfolio
The project featured in this ePortfolio is a thermostat prototype that keeps track of how many hours the heat and A/C run every day and a web-based dashboard that uses that data to display different monthly metrics. The TI SimpleLink CC3220S Launchpad is the board used for this prototype. It contains two buttons and a temperature sensor, and it is programmed using the C language. It stores a set temperature that can be lowered or raised using the buttons. Based on the difference between the room temperature and the set temperature, the powering on of the heat or air conditioning is simulated and the amount of time each is running is counted in seconds. At the end of the day, the seconds are converted to hours and stored in a .csv file and all counters are reset.
insertData.php is a server-side script that reads data from the .csv file and sends it to the database. The database stores three pieces of information: the date, the number of hours the heat was on, and the number of hours the A/C was on. On the client side, getData.php connects to the database and queries for all entries from the current month. Another file, operations.php, calculates the approximate wattage and costs associated with heating and cooling. Finally, index.php uses HTML and Canvas.js with all the gathered data to render charts and organize them on the page to create the dashboard.

```markdown



## The Process
insert narratives here

## How it turned out
insert dashboard image (clicking will open the page)
```
## How it began
I started by reviewing the code of my existing project.

[![Error playing video](https://www.youtube.com/watch?v=glA8dEty4Rw)


### Server Side Files
- [thermostat_prototype.c](https://github.com/Kelsey-Stokes/ePortfolio/blob/gh-pages/Back%20End/Thermostat_Prototype/thermostat_prototype.c)
- [dataInsert.php](https://github.com/Kelsey-Stokes/ePortfolio/blob/gh-pages/Back%20End/dataInsert.php)
- [Microprocessor Configuration File](https://github.com/Kelsey-Stokes/ePortfolio/blob/gh-pages/Back%20End/Thermostat_Prototype/gpiointerrupt.syscfg)

### Client Side Files
- [index.php](https://github.com/Kelsey-Stokes/ePortfolio/blob/gh-pages/Front%20End/index.php)
- [operations.php](https://github.com/Kelsey-Stokes/ePortfolio/blob/gh-pages/Front%20End/operations.php)


**Bold** and _Italic_ and `Code` text

[Link](url) and ![Image](src)


For more details see [Basic writing and formatting syntax](https://docs.github.com/en/github/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax).

### Jekyll Themes

Your Pages site will use the layout and styles from the Jekyll theme you have selected in your [repository settings](https://github.com/Kelsey-Wyer/ePortfolio/settings/pages). The name of this theme is saved in the Jekyll `_config.yml` configuration file.

### Support or Contact

Having trouble with Pages? Check out our [documentation](https://docs.github.com/categories/github-pages-basics/) or [contact support](https://support.github.com/contact) and we’ll help you sort it out.
