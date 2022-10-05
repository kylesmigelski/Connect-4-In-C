
STUDENT_ENGINE_FILES = src/connect4_engine.c
STUDENT_MAIN_FILE = src/c4.c

# Don't change the name of the executable.  The automated tests depend on it.
c4:	$(STUDENT_MAIN_FILE) $(STUDENT_ENGINE_FILES) 
	gcc -Wall -I src $^ -o $@

studentTests: $(STUDENT_ENGINE_FILES) test/student_test.c unity/unity.c
	gcc -Wall -I src -I unity $^ -o $@

# The if below is so no errors occur if the files don't exist
clean:
	if [ -f *.o ]; then rm *.o; fi
	if [ -f c4 ]; then rm c4; fi
	if [ -f studentTests ]; then rm studentTests; fi
	if [ -f instructorTests ]; then rm instructorTests; fi
	rm testCheckers/testChecker*
