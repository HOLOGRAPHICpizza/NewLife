package org.peak15.newlife.types.statement;


public final class CallStatement implements Statement {
	
	private final String call;
	
	public CallStatement(String call) {
		if(call == null) {
			throw new NullPointerException("Call string may not be null.");
		}
		else if(call.length() < 1) {
			throw new IllegalArgumentException("Call string may not be empty.");
		}
		
		this.call = call;
	}
	
	public String getCall() {
		return call;
	}
	
	@Override
	public boolean equals(Object obj) {
		if(obj == this) {
			return true;
		}
		
		if(!(obj instanceof CallStatement)) {
			return false;
		}
		
		CallStatement s = (CallStatement) obj;
		
		return s.getCall().equals(this.getCall());
	}
	
	@Override
	public int hashCode() {
		int result = 9001;
		result = 1327 * result + this.getCall().hashCode();
		return result;
	}
	
	@Override
	public String toString() {
		return String.format("(CALL: %s)", this.getCall());
	}
}
