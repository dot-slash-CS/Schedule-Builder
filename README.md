# A Schedule Visualization Tool for WebAdvisor

WebAdvisor is Ohlone Community College's student portal, through which students register for courses, among other functions.

WebAdvisor's interface is somewhat muddly and difficult to work through, but especially so when you're trying to figure out when exactly your classes are and what your weekly schedule looks like. The site has no present capacity for students to view their weekly courseload in a calendar layout. This projects aims to develop a web application that can take care of that automatically.

This project is intended to be a proof of concept. The main feature is the single-week calendar display, and the goal is to have this feature approved and implemented in WebAdvisor. The WebDriver backend is not intended to make it to production.

## Execution Essentials

To run *ScheduleBuilder* for testing, you will need:
- [Python3](https://www.python.org/downloads/) (popular high-level programming language)
- [pip](https://pip.pypa.io/en/stable/installing/) (package manager for Python)
- [Selenium WebDriver](http://www.seleniumhq.org/docs/03_webdriver.jsp) (tool for scripted/programmatic web browsing)
- [ChromeDriver](https://sites.google.com/a/chromium.org/chromedriver/) (GUI browser)
- [PhantomJS](http://phantomjs.org/) (GUI-less, or "headless", browser)

To set everything up to run *ScheduleBuilder*:
- have Python and Selenium WebDriver installed
- have the ChromeDriver and PhantomJS executables in the same directory as the Python files
- install the required Python packages using the command `pip3 install -r requirements.txt`
    * It's recommended that you utilize [Virtual Environments](http://docs.python-guide.org/en/latest/dev/virtualenvs/), but that's complicated and optional.

To run *ScheduleBuilder*:
- navigate to the directory containing the Python files in command line
- use the command `python3 parser.py`.
- open your web browser and navigate to `http://localhost:5000/`

## Current Capabilities

At the moment, *ScheduleBuilder*:
- takes course identification information for a number of sections from the user through a webpage
- searches WebAdvisor for the sections using Selenium WebDriver
- parses section information from the Section Information page using regex

At the moment, *ScheduleBuilder* does not:
- store course information in JSON
- display weekly semester courseload in a single-week calendar layout using JavaScript

## Miscellaneous Mentions

Built by Ohlone Students, for Ohlone Students.

Developed and tested with Python 3.6.0 on macOS Sierra 10.12.3
