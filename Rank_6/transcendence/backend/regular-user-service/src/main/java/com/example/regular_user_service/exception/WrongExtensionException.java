package com.example.regular_user_service.exception;

public class WrongExtensionException extends RuntimeException{
	public WrongExtensionException(String error) {
		super(error);
	}
}