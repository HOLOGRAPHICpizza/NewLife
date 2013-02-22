package org.peak15.newlife.types;

public final class WhileStatement implements Statement {

	private final Condition condition;
	private final BlockStatement body;
	
	/**
	 * Construct a while statement.
	 * 
	 * @param condition to execute body while true.
	 * @param body block to execute while true.
	 */
	public WhileStatement(Condition condition, BlockStatement body) {
		if(condition == null || body == null) {
			throw new NullPointerException("WhileStatement needs a condition and body.");
		}
		
		this.condition = condition;
		this.body = body;
	}
	
	public Condition getCondition() {
		return this.condition;
	}
	
	public BlockStatement getBody() {
		return this.body;
	}
	
	@Override
	public boolean equals(Object obj) {
		if(obj == this) {
			return true;
		}
		
		if(!(obj instanceof WhileStatement)) {
			return false;
		}
		
		WhileStatement s = (WhileStatement) obj;
		
		return	s.getCondition().equals(this.getCondition()) &&
				s.getBody().equals(this.getBody());
	}
	
	@Override
	public int hashCode() {
		int result = 9001;
		result = 1327 * result + this.getCondition().hashCode();
		result = 1327 * result + this.getBody().hashCode();
		return result;
	}
	
	@Override
	public String toString() {
		return String.format("(WHILE %s: %s)", this.getCondition(), this.getBody());
	}
}
