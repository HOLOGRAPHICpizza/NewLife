package org.peak15.newlife.types;

import java.util.Collections;
import java.util.LinkedList;
import java.util.List;

/**
 * One abstract blargStatement of code.
 * 
 * Immutable.
 */
public final class BlargStatement {
	public enum StatementType {
		BLOCK,
		IF,
		IF_ELSE,
		WHILE,
		CALL
	}
	
	public enum Condition {
		NEXT_IS_EMPTY,
		NEXT_IS_NOT_EMPTY,
		NEXT_IS_WALL,
		NEXT_IS_FRIEND,
		NEXT_IS_ENEMY,
		NEXT_IS_NOT_ENEMY,
		RANDOM,
		TRUE
	}
	
	private final StatementType type;
	private final List<BlargStatement> blargStatements;
	private final Condition condition;
	private final String instruction;
	
	/**
	 * Construct a BLOCK blargStatement.
	 * 
	 * @param blargStatements The blargStatements in the block.
	 */
	public static BlargStatement makeBlock(List<BlargStatement> blargStatements) {
		return new BlargStatement(
				StatementType.BLOCK,
				new LinkedList<BlargStatement>(blargStatements),
				null,
				null);
	}
	
	/**
	 * Construct an IF blargStatement.
	 * 
	 * @param cond condition for the blargStatement
	 * @param body code to execute if true
	 */
	public static BlargStatement makeIf(Condition cond, BlargStatement body) {
		if(cond == null || body == null) {
			throw new NullPointerException();
		}
		
		return new BlargStatement(
				StatementType.IF,
				Collections.singletonList(body),
				cond,
				null);
	}
	
	/**
	 * Construct an IF_ELSE blargStatement.
	 * 
	 * @param cond condition for the blargStatement
	 * @param body code to execute if true
	 * @param elseBody code to execute if false
	 */
	public static BlargStatement makeIfElse(Condition cond, BlargStatement body, BlargStatement elseBody) {
		if(cond == null || body == null || elseBody == null) {
			throw new NullPointerException();
		}
		
		List<BlargStatement> blargStatements = new LinkedList<>();
		blargStatements.add(body);
		blargStatements.add(elseBody);
		
		return new BlargStatement(
				StatementType.IF_ELSE,
				blargStatements,
				cond,
				null);
	}
	
	/**
	 * Construct a CALL blargStatement.
	 * 
	 * @param instruction
	 */
	public static BlargStatement makeCall(String instruction) {
		if(instruction == null) {
			throw new NullPointerException();
		}
		
		return new BlargStatement(
				StatementType.CALL,
				null,
				null,
				instruction);
	}
	
	/**
	 * Construct a WHILE blargStatement.
	 * 
	 * @param condition execute body while this is true
	 * @param body BLOCK blargStatement to execute while condition holds
	 * @return WHILE blargStatement with given components
	 */
	public static BlargStatement makeWhile(Condition condition, BlargStatement body) {
		if(condition == null || body == null) {
			throw new NullPointerException();
		}
		if(body.type != StatementType.BLOCK) {
			throw new IllegalArgumentException("body is not a BLOCK blargStatement");
		}
		
		return new BlargStatement(
				StatementType.WHILE,
				Collections.singletonList(body),
				condition,
				null);
	}
	
	private BlargStatement(StatementType type, List<BlargStatement> blargStatements,
			Condition condition, String instruction) {
		this.type = type;
		this.blargStatements = blargStatements;
		this.condition = condition;
		this.instruction = instruction;
	}
	
	public StatementType getType() {
		return type;
	}
	
	/**
	 * Only valid for blargStatements with conditions.
	 * 
	 * @return the condition
	 */
	public Condition getCondition() {
		switch(type) {
		case IF:
		case IF_ELSE:
		case WHILE:
			break;
		
		default:
			throw new UnsupportedOperationException();
		}
		
		return condition;
	}
	
	/**
	 * Only valid for CALL blargStatements.
	 * 
	 * @return the call instruction
	 */
	public String getInstruction() {
		if(type != StatementType.CALL) {
			throw new UnsupportedOperationException();
		}
		
		return instruction;
	}
	
	/**
	 * For BLOCKs, the body of blargStatements.
	 * For IF(_ELSE)s, the body, then the elseBody (if any).
	 * For WHILEs, the body of blargStatements.
	 * 
	 * Invalid for other blargStatement types.
	 * 
	 * @return the list of blargStatements within this blargStatement
	 */
	public List<BlargStatement> getStatements() {
		switch(type) {
		case BLOCK:
		case IF:
		case IF_ELSE:
		case WHILE:
			break;
		
		default:
			throw new UnsupportedOperationException();
		}
		
		return Collections.unmodifiableList(blargStatements);
	}
	
	@Override
	public boolean equals(Object obj) {
		if(obj == this) {
			return true;
		}
		
		if(!(obj instanceof BlargStatement)) {
			return false;
		}
		
		BlargStatement s = (BlargStatement) obj;
		
		if(s.getType() != this.getType()) {
			return false;
		}
		
		switch(s.getType()) {
		case BLOCK:
			return s.getStatements().equals(this.getStatements());
			
		case CALL:
			return s.getInstruction().equals(this.getInstruction());
			
		case IF:
		case IF_ELSE:
		case WHILE:
			return	s.getCondition() == this.getCondition() &&
					s.getStatements().equals(this.getStatements());
		
		default:
			throw new UnsupportedOperationException();
		}
	}
	
	@Override
	public int hashCode() {
		int result = 9001;
		
		result = 1327 * result + this.getType().hashCode();
		
		switch(this.getType()) {
		case BLOCK:
			result = 1327 * result + this.getStatements().hashCode();
			break;
			
		case CALL:
			result = 1327 * result + this.getInstruction().hashCode();
			break;
			
		case IF:
		case IF_ELSE:
		case WHILE:
			result = 1327 * result + this.getCondition().hashCode();
			result = 1327 * result + this.getStatements().hashCode();
			break;
		
		default:
			throw new UnsupportedOperationException();
		}
		
		return result;
	}
	
	@Override
	public String toString() {
		StringBuilder desc = new StringBuilder();
		
		switch(this.getType()) {
		case BLOCK:
			desc.append(this.getStatements().size()).append(" blargStatements");
			break;
			
		case CALL:
			desc.append(this.getInstruction());
			break;
			
		case IF:
		case WHILE:
		case IF_ELSE:
			desc.append(this.condition.toString());
			
			for(BlargStatement s : this.getStatements()) {
				desc.append(", ").append(s.toString());
			}
			break;
		
		default:
			throw new UnsupportedOperationException();
		}
		return String.format("(%s, %s)", this.getType().toString(), desc.toString());
	}
}
