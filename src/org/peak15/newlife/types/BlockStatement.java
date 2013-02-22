package org.peak15.newlife.types;

import java.util.Collections;
import java.util.LinkedList;
import java.util.List;

/**
 * List of zero or more statements.
 */
public final class BlockStatement implements Statement {
	
	private final List<Statement> list;
	
	/**
	 * @param statements a list of zero or more statements.
	 */
	public BlockStatement(List<Statement> statements) {
		if(statements == null) {
			throw new NullPointerException();
		}
		
		this.list = new LinkedList<>(statements);
	}
	
	public static class Builder {
		
		private List<Statement> list = new LinkedList<>();
		
		public Builder() {}
		
		public Builder append(Statement statement) {
			if(statement == null) {
				throw new NullPointerException();
			}
			
			list.add(statement);
			return this;
		}
		
		public BlockStatement build() {
			return new BlockStatement(list);
		}
	}
	
	public List<Statement> getStatements() {
		return Collections.unmodifiableList(list);
	}
	
	@Override
	public boolean equals(Object obj) {
		if(obj == this) {
			return true;
		}
		
		if(!(obj instanceof BlockStatement)) {
			return false;
		}
		
		BlockStatement s = (BlockStatement) obj;
		
		return s.getStatements().equals(this.getStatements());
	}
	
	@Override
	public int hashCode() {
		int result = 9001;
		result = 1327 * result + this.getStatements().hashCode();
		return result;
	}
	
	@Override
	public String toString() {
		return String.format("<block: %d statements>", this.getStatements().size());
	}
}
