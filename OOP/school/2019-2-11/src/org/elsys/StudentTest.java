package org.elsys;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;


public class StudentTest {


    @Test
    public void testGetStudentName(){
        Student student = new Student(1, "Mihail", "Kirov");
        Assertions.assertEquals("Mihail", student.getFirstName());
    }
}
