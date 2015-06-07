import javax.crypto.Mac;
import javax.crypto.SecretKey;
import javax.crypto.spec.SecretKeySpec;

public class HMAC {

	public static byte[] Encrypt(String secKey, String input) {
		return Encrypt("HMACSHA256", secKey, input);
	}

	public static byte[] Encrypt(String method, String secKey, String input) {
		try {
			Mac mac = Mac.getInstance(method);
			// get the bytes of the hmac key and data string
			SecretKey secret = new SecretKeySpec(secKey.getBytes("UTF-8"), method);
			mac.init(secret);
			byte[] doFinal = mac.doFinal(input.getBytes("UTF-8"));
			return doFinal;
		} catch (Exception e) {
			throw new RuntimeException(e);
		}
	}

	public static String bytes2Hex(byte[] bts) {
		String des = "";
		String tmp = null;
		for (int i = 0; i < bts.length; i++) {
			tmp = (Integer.toHexString(bts[i] & 0xFF));
			if (tmp.length() == 1) {
				des += "0";
			}
			des += tmp;
		}
		return des;
	}
}
