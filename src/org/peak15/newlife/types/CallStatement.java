package org.peak15.newlife.types;

public final class CallStatement implements Statement {
	
	private final String call;
	
	public CallStatement(String call) {
		this.call = call;
	}
	
	public String getCall() {
		return call;
	}
	
}
