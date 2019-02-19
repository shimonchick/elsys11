package org.elsys;

public class Student {

    private long id;

    private String firstName;
    private String lastName;

    public Student(){
        this.id = 0;
        this.firstName = "";
        this.lastName = "";
    }

    public Student(long id, String firstName, String lastName) {
        this.id = id;
        this.firstName = firstName;
        this.lastName = lastName;
    }

    public java.lang.String getFirstName() {
        return firstName;
    }


    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }
    public String getLastName(){
            return  lastName;
    }
    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public long getId() {
        return id;
    }

    @Override
    public String toString() {
        return "Student{" +
                "id=" + id +
                ", firstName='" + firstName + '\'' +
                ", lastName='" + lastName + '\'' +
                '}';
    }

    @Override
    public boolean equals(Object obj) {
        if(obj == null) {
            return false;
        }
        Student other = (Student)obj;
        return this.id == other.id
                && this.firstName == other.firstName
                && this.lastName == other.lastName;

    }


    @Override
    public int hashCode() {
        int result = 0;
        final int prime = 17;
        result = (int)id
                + firstName.hashCode() * prime
                + lastName.hashCode();

        return result;
    }

}
