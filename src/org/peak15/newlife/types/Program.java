package org.peak15.newlife.types;

import java.util.Collections;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

/**
 * One abstract program.
 * 
 * Immutable.
 */
public final class Program {
	private final String name;
	private final Map<String, Statement> context;
	private final Statement body;
	
	public Program(String name, Map<String, Statement> context, Statement body) {
		this.name = name;
		this.context = new HashMap<String, Statement>(context);
		this.body = body;
	}

	/**
	 * @return the name
	 */
	public String getName() {
		return name;
	}

	/**
	 * @return the context
	 */
	public Map<String, Statement> getContext() {
		return Collections.unmodifiableMap(context);
	}

	/**
	 * @return the body
	 */
	public Statement getBody() {
		return body;
	}
	
	@Override
	public boolean equals(Object obj) {
		if(obj == this) {
			return true;
		}
		
		if(!(obj instanceof Program)) {
			return false;
		}
		
		Program p = (Program) obj;
		
		return	p.getName().equals(this.getName()) &&
				p.getBody().equals(this.getBody()) &&
				p.getContext().equals(this.getContext());
	}
	
	@Override
	public int hashCode() {
		int result = 9001;
		result = 1327 * result + this.getName().hashCode();
		result = 1327 * result + this.getBody().hashCode();
		result = 1327 * result + this.getContext().hashCode();
		return result;
	}
	
	@Override
	public String toString() {
		StringBuilder conDesc = new StringBuilder();
		
		Iterator<String> i = this.getContext().keySet().iterator();
		while(i.hasNext()) {
			conDesc.append(i.next());
			
			if(i.hasNext()) {
				conDesc.append(", ");
			}
		}
		
		return String.format(
				"(name: %s, context: {%s}, body: %s)",
				this.getName(),
				conDesc.toString(),
				this.getBody().toString());
	}
}
