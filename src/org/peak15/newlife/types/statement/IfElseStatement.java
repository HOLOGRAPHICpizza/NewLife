package org.peak15.newlife.types.statement;

public final class IfElseStatement implements Statement {

	private final Condition condition;
	private final BlockStatement body, elseBody;
	
	/**
	 * Construct an if statement.
	 * 
	 * @param condition to execute body when true
	 * @param body block to execute when true.
	 */
	public IfElseStatement(Condition condition, BlockStatement body) {
		this(condition, body, BlockStatement.emptyBlock());
	}
	
	/**
	 * Construct an if else statement.
	 * 
	 * @param condition to execute body when true, or elseBody when false.
	 * @param body block to execute when true.
	 * @param elseBody block to execute when false.
	 */
	public IfElseStatement(Condition condition, BlockStatement body, BlockStatement elseBody) {
		if(condition == null || body == null || elseBody == null) {
			throw new NullPointerException("No paramaters may be null.");
		}
		
		this.condition = condition;
		this.body = body;
		this.elseBody = elseBody;
	}
	
	public Condition getCondition() {
		return this.condition;
	}
	
	public BlockStatement getBody() {
		return this.body;
	}
	
	public BlockStatement getElseBody() {
		return this.elseBody;
	}
	
	@Override
	public boolean equals(Object obj) {
		if(obj == this) {
			return true;
		}
		
		if(!(obj instanceof IfElseStatement)) {
			return false;
		}
		
		IfElseStatement s = (IfElseStatement) obj;
		
		return	s.getCondition().equals(this.getCondition()) &&
				s.getBody().equals(this.getBody()) &&
				s.getElseBody().equals(this.getElseBody());
	}
	
	@Override
	public int hashCode() {
		int result = 9001;
		result = 1327 * result + this.getCondition().hashCode();
		result = 1327 * result + this.getBody().hashCode();
		result = 1327 * result + this.getElseBody().hashCode();
		return result;
	}
	
	@Override
	public String toString() {
		String elseDesc = "";
		if(this.getElseBody().size() > 0) {
			elseDesc = ", ELSE: " + this.getElseBody().toString();
		}
		
		return String.format("(IF %s: %s%s)", this.getCondition(), this.getBody(), elseDesc);
	}
}
