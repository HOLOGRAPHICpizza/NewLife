package org.peak15.newlife.test.types;

import java.util.Collections;
import org.peak15.newlife.types.BlargStatement;
import org.peak15.newlife.types.BlargStatement.Condition;

public class StatementTest extends ValueTypeTest<BlargStatement> {
	
	//TODO: Currently tests only a few of the blargStatement types
	//		with the standard value type tests.
	
	//TODO: Test the various constructors.
	
	@Override
	protected BlargStatement A() {
		BlargStatement body = BlargStatement.makeBlock(
				Collections.singletonList(BlargStatement.makeCall("explode")));
		
		BlargStatement elseBody = BlargStatement.makeBlock(
				Collections.singletonList(BlargStatement.makeCall("explode")));
		
		return BlargStatement.makeIfElse(Condition.RANDOM, body, elseBody);
	}

	@Override
	protected BlargStatement D() {
		return BlargStatement.makeCall("blarg");
	}
}
