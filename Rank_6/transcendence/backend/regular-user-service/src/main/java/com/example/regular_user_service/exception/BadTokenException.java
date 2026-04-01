package com.example.regular_user_service.exception;

public class BadTokenException extends RuntimeException{
	public BadTokenException(String error) {
		super(error);
	}
}