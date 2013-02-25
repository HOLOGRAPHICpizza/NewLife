package org.peak15.newlife.types.statement;

import org.peak15.newlife.Condition;

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
			throw new NullPointerException("No parameters may be null.");
		}
		
		this.condition = condition;
		this.body = body;
	}
	
	public Condition condition() {
		return this.condition;
	}
	
	public BlockStatement body() {
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
		
		return	s.condition().equals(this.condition()) &&
				s.body().equals(this.body());
	}
	
	@Override
	public int hashCode() {
		int result = 9001;
		result = 1327 * result + this.condition().hashCode();
		result = 1327 * result + this.body().hashCode();
		return result;
	}
	
	@Override
	public String toString() {
		return String.format("(WHILE %s: %s)", this.condition(), this.body());
	}
}
