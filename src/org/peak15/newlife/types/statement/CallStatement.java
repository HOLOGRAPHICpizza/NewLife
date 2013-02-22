package org.peak15.newlife.types.statement;


public final class CallStatement implements Statement {
	
	private final String call;
	
	public CallStatement(String callString) {
		if(callString == null) {
			throw new NullPointerException("Call string may not be null.");
		}
		/*else if(callString.length() < 1) {
			throw new IllegalArgumentException("Call string may not be empty.");
		}*/
		
		this.call = callString;
	}
	
	/**
	 * @return the name of the instruction called by this statement.
	 */
	public String instructionName() {
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
		
		return s.instructionName().equals(this.instructionName());
	}
	
	@Override
	public int hashCode() {
		int result = 9001;
		result = 1327 * result + this.instructionName().hashCode();
		return result;
	}
	
	@Override
	public String toString() {
		return String.format("(CALL: %s)", this.instructionName());
	}
}
