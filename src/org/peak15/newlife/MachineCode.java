package org.peak15.newlife;

import java.util.Collections;
import java.util.LinkedList;
import java.util.List;

import org.peak15.newlife.types.StaticBiMap;

public enum MachineCode {
	MOVE,
	TURNLEFT,
	TURNRIGHT,
	INFECT,
	SKIP,
	HALT,
	JUMP,
	JUMP_IF_NOT_NEXT_IS_EMPTY,
	JUMP_IF_NOT_NEXT_IS_NOT_EMPTY,
	JUMP_IF_NOT_NEXT_IS_WALL,
	JUMP_IF_NOT_NEXT_IS_NOT_WALL,
	JUMP_IF_NOT_NEXT_IS_FRIEND,
	JUMP_IF_NOT_NEXT_IS_NOT_FRIEND,
	JUMP_IF_NOT_NEXT_IS_ENEMY,
	JUMP_IF_NOT_NEXT_IS_NOT_ENEMY,
	JUMP_IF_NOT_RANDOM,
	JUMP_IF_NOT_TRUE;
	
	private static final StaticBiMap<MachineCode, Byte> map = new StaticBiMap.Builder<MachineCode, Byte>()
			.append(MOVE,							(byte) 0x00)
			.append(TURNLEFT,						(byte) 0x01)
			.append(TURNRIGHT,						(byte) 0x02)
			.append(INFECT,							(byte) 0x03)
			.append(SKIP,							(byte) 0x04)
			.append(HALT,							(byte) 0x05)
			.append(JUMP,							(byte) 0x06)
			.append(JUMP_IF_NOT_NEXT_IS_EMPTY,		(byte) 0x07)
			.append(JUMP_IF_NOT_NEXT_IS_NOT_EMPTY,	(byte) 0x08)
			.append(JUMP_IF_NOT_NEXT_IS_WALL,		(byte) 0x09)
			.append(JUMP_IF_NOT_NEXT_IS_NOT_WALL,	(byte) 0x0A)
			.append(JUMP_IF_NOT_NEXT_IS_FRIEND,		(byte) 0x0B)
			.append(JUMP_IF_NOT_NEXT_IS_NOT_FRIEND,	(byte) 0x0C)
			.append(JUMP_IF_NOT_NEXT_IS_ENEMY,		(byte) 0x0D)
			.append(JUMP_IF_NOT_NEXT_IS_NOT_ENEMY,	(byte) 0x0E)
			.append(JUMP_IF_NOT_RANDOM,				(byte) 0x0F)
			.append(JUMP_IF_NOT_TRUE,				(byte) 0x10)
			.build();
	
	public static MachineCode ofByte(byte b) {
		return map.keyOf(b);
	}
	
	//TODO: should this be toByte()?
	public byte asByte() {
		return map.valueOf(this);
	}
	
	public static List<MachineCode> listFromBytes(List<Byte> bytes) {
		List<MachineCode> ret = new LinkedList<>();
		for(byte b : bytes) {
			ret.add(MachineCode.ofByte(b));
		}
		return Collections.unmodifiableList(ret);
	}
	
	public static List<Byte> bytesFromList(List<MachineCode> list) {
		List<Byte> ret = new LinkedList<>();
		for(MachineCode c : list) {
			ret.add(c.asByte());
		}
		return Collections.unmodifiableList(ret);
	}
}
