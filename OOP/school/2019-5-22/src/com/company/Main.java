package com.company;

import java.lang.reflect.Constructor;
import java.lang.reflect.Field;

public class Main {

    public static void main(String[] args) {
        Bill bill = new BillHundred();
        Class<? extends Bill> billClass = bill.getClass();

        System.out.println(billClass.getSimpleName());
        System.out.println(billClass.getSuperclass());
        for (Class<?> billClassInterface : billClass.getInterfaces()) {
            System.out.println(billClassInterface.getSimpleName());
        }
        for (Constructor<?> declaredConstructor : billClass.getDeclaredConstructors()) {
            System.out.println(declaredConstructor);
        }
        for (Field field : billClass.getDeclaredFields()) {
            System.out.println(field);
        }
        try {
            System.out.println(billClass.getDeclaredMethod("getValue"));
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        }


    }

    public static String serialize(Object obj) {
        StringBuilder result = new StringBuilder();
        Class<?> objClass = obj.getClass();
        result.append("FQN/\n");
        for (Field declaredField : objClass.getDeclaredFields()) {

            result.append(declaredField.getName());
            result.append(" = ");
            Boolean shouldChange = false;
            if (!declaredField.isAccessible()) {
                declaredField.setAccessible(true);
                shouldChange = true;
            }

            try {
                result.append(declaredField.get(obj));
            } catch (IllegalAccessException e) {
                e.printStackTrace();
            }
            if(shouldChange){
                declaredField.setAccessible(false);
            }
            result.append("\n");
        }
        result.append("\n/FQN");

        return result.toString();
    }
}
