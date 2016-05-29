#A Schedule Visualization Tool for WebAdvisor

WebAdvisor's interface is somewhat muddly and difficult to work through, but especially so when you're trying to figure out when exactly your classes are and what your weekly schedule looks like. This projects aims to develop a web application that can take care of that automatically.

##Execution Essentials

To run *ScheduleBuilder* for testing, you will need:
- [Python](https://www.python.org/downloads/) (popular high-level programming language)
- [pip](https://pip.pypa.io/en/stable/installing/) (package manager for Python)
- [Selenium WebDriver](http://www.seleniumhq.org/docs/03_webdriver.jsp) (tool for scripted/programmatic web browsing)
- [ChromeDriver](https://sites.google.com/a/chromium.org/chromedriver/) (GUI browser)
- [PhantomJS](http://phantomjs.org/) (GUI-less, or "headless", browser)

To set everything up to run *ScheduleBuilder*:
- have Python and Selenium WebDriver installed
- have the ChromeDriver and PhantomJS executables in the same directory as the Python files
- install the required Python packages using the command `pip install -r requirements.txt`
    * It's recommended that you utilize [Virtual Environments](http://docs.python-guide.org/en/latest/dev/virtualenvs/), but that's complicated and optional.

To run *ScheduleBuilder*:
- navigate to the directory containing the Python files in command line
- use the command `python parser.py`.
- open your web browser and navigate to `http://localhost:5000/`

##Current Capabilities

At the moment, *ScheduleBuilder*:
- takes course identification information for a number of sections from the user through a webpage
- searches WebAdvisor for the sections
- parses section information from the Section Information page

##Miscellaneous Mentions

Built by Ohlone Students, for Ohlone Students.

Developed and tested with Python 2.7.11 on Mac OS X 10.11.5
