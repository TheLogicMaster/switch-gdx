package java.util;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Formatter {

	private String formatted;

	public Formatter() {

	}

	public Formatter format(String format, Object ... args) {
		Matcher matcher = Pattern.compile("%s").matcher(format);
		StringBuffer buffer = new StringBuffer();
		System.out.println("Matches: " + matcher.matches());
		int i = 0;
		while (matcher.find()) {
			if (i >= args.length)
				throw new IllegalFormatException();
			matcher.appendReplacement(buffer, args[i++].toString());
		}
		matcher.appendTail(buffer);
		formatted = buffer.toString();
		return this;
	}

	@Override
	public String toString () {
		return formatted;
	}
}
