from selenium import webdriver
from selenium.webdriver.support.ui import Select
from selenium.webdriver.common.keys import Keys
from selenium.common.exceptions import NoSuchElementException
from course import Course

def main():
    # Get desired course from console user input
    data = []

    # This input method is just for testing
    term    = raw_input("Input term (2015SU, 2015FA, 2016SP): ").upper()
    subject = raw_input("Input subject code:                  ").upper()
    course  = raw_input("Input course number:                 ").upper()
    section = raw_input("Input section number:                ").upper()
    data.append([term, subject, course, section])
    term    = raw_input("Input term (2015SU, 2015FA, 2016SP): ").upper()
    subject = raw_input("Input subject code:                  ").upper()
    course  = raw_input("Input course number:                 ").upper()
    section = raw_input("Input section number:                ").upper()
    data.append([term, subject, course, section])

    courses = scrape_courses(data)

def scrape_courses(data):
    '''Returns a list of courses gathered from data.

    Arg data -- a list of four-element lists of the form [term, subject, course, section] where each element is a string
    '''
    course_list = []
    # Instantiate WebDriver
    driver = webdriver.Chrome("/Users/siphe24/documents/projects/exploration/parser/chromedriver") # GUI browser, for testing
    #driver = webdriver.PhantomJS("/Users/siphe24/documents/projects/exploration/parser/phantomjs") # Headless browser, for deploying

    for l in data:
        # Access WebAdvisor section search page
        driver.get("https://webadvisor.ohlone.edu/WebAdvisor/WebAdvisor?CONSTITUENCY=WBST&type=P&pid=ST-XWESTS12A")
        # Select term from drop-down menu
        try:
            Select(driver.find_element_by_id('VAR1')).select_by_value(l[0])
        except NoSuchElementException:
            print "Invalid Term"
            driver.quit()
            return
        # Select subject from drop-down menu
        try:
            Select(driver.find_element_by_id('LIST_VAR1_1')).select_by_value(l[1])
        except NoSuchElementException:
            print "Invalid Subject"
            driver.quit()
            return
        # Input course via text box
        driver.find_element_by_id('LIST_VAR3_1').send_keys(l[2])
        # Input section via text box
        driver.find_element_by_id('LIST_VAR4_1').send_keys(l[3])
        # Submit search parameters
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

        # Create a Section object using course information
        try:
            course_list.append(Course(VAR1, VAR2, VAR4, VAR12_1))
        except ValueError:
            print "Not enough information available from WebAdvisor"

        # Close tab and reset focus
        driver.close()
        driver.switch_to.window(driver.window_handles[0])

    driver.quit()

    # Print courses to console, for testing
    for course in course_list:
        course.print_info()

main()
