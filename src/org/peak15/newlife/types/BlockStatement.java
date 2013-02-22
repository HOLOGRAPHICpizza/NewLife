package org.peak15.newlife.types;

import java.util.Collections;
import java.util.LinkedList;
import java.util.List;

/**
 * List of one or more statements.
 */
public final class BlockStatement implements Statement {
	
	private final List<Statement> list;
	
	/**
	 * @param statements a list of one or more statements.
	 */
	public BlockStatement(List<Statement> statements) {
		if(statements == null) {
			throw new NullPointerException("No parameters may be null.");
		}
		else if(statements.size() < 1) {
			throw new IllegalArgumentException("A block must contain at least one statement.");
		}
		
		this.list = new LinkedList<>(statements);
	}
	
	public static class Builder {
		
		private List<Statement> list = new LinkedList<>();
		
		/**
		 * Empty constructor for syntax convenience.
		 */
		public Builder() {}
		
		public Builder(Statement first) {
			this.append(first);
		}
		
		public Builder append(Statement statement) {
			if(statement == null) {
				throw new NullPointerException("Blocks may not contain null statements.");
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
	
	public int size() {
		return list.size();
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
		return String.format("<block: %d statements>", this.size());
	}
}
