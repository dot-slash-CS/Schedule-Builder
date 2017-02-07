import os

from flask import Flask, request

# Use the Selenium WebDriver to access internet
from selenium import webdriver
from selenium.webdriver.support.ui import Select
from selenium.webdriver.common.keys import Keys
from selenium.common.exceptions import NoSuchElementException
from course import Course

app = Flask(__name__)

@app.route("/")
def index():
    return app.send_static_file("index.html")

@app.route("/query", methods=["post"])
def query():
    term = request.form['term']
    subject = request.form['subject']
    courseNum = request.form['courseNum']
    sectionNum = request.form['sectionNum']
    data = [term, subject, courseNum, sectionNum]
    course = scrape_courses(data)
    return "Success!"

def scrape_courses(data):
    '''Returns the course gathered from data.

    Arg data -- a four-element list of the form [term, subject, courseNum, sectionNum] where each element is a string
    '''
    # Instantiate WebDriver; assumes executables are in the same directory as this script
    driver = webdriver.Chrome(os.path.join(os.path.abspath(os.path.dirname(__file__)), "chromedriver")) # GUI browser, for testing
    #driver = webdriver.PhantomJS(os.path.join(os.path.abspath(os.path.dirname(__file__)), "phantomjs")) # Headless browser, for deploying

    # Access WebAdvisor main page
    driver.get("https://webadvisor.ohlone.edu/WebAdvisor/WebAdvisor")

    # Navigate to search page
    driver.find_element_by_link_text('Search for Sections').click()

    # Select term from drop-down menu
    try:
        Select(driver.find_element_by_id('VAR1')).select_by_value(data[0])
    except NoSuchElementException: # This shouldn't happen if validation is in place
        print "Invalid Term"
        driver.quit()
        return
    # Select subject from drop-down menu
    try:
        Select(driver.find_element_by_id('LIST_VAR1_1')).select_by_value(data[1])
    except NoSuchElementException: # This shouldn't happen if validation is in place
        print "Invalid Subject"
        driver.quit()
        return
    # Input course via text box
    driver.find_element_by_id('LIST_VAR3_1').send_keys(data[2])
    # Input section via text box
    driver.find_element_by_id('LIST_VAR4_1').send_keys(data[3])
    # Submit search parameters via the "SUBMIT" button
    driver.find_element_by_name('SUBMIT2').click()
    # Select the desired course, which will open a new tab
    try:
        driver.find_element_by_id('SEC_SHORT_TITLE_1').click()
    except NoSuchElementException:
        print "No such Course/Section found."
        driver.quit()
        return
    # Set focus to new tab
    driver.switch_to.window(driver.window_handles[1])

    # Parse for course information
    VAR1 = driver.find_element_by_id('VAR1').text             # Contains title
    VAR2 = driver.find_element_by_id('VAR2').text             # Contains subject, course number, and section
    VAR4 = driver.find_element_by_id('VAR4').text             # Contains credits
    VAR12_1 = driver.find_element_by_id('LIST_VAR12_1').text  # Contains everything else

    # Create a Section object using course information and add it to the list
    try:
        course = Course(VAR1, VAR2, VAR4, VAR12_1)
    except ValueError:
        print "Not enough information available from WebAdvisor"

    driver.quit()

    return course

class InvalidTerm(TypeError):
    def __init__(self):
        TypeError.__init__(self, "Invalid term entered.")

class InvalidSubject(TypeError):
    def __init__(self):
        TypeError.__init__(self, "Invalid subject entered.")

if __name__ == "__main__":
    app.run(debug=True)
