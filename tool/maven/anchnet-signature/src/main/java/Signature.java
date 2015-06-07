/**
 * Created with IntelliJ IDEA.
 * User: anchnet-002
 * Date: 15-3-17
 * To change this template use File | Settings | File Templates.
 */
import java.util.Base64;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Signature {

  public static String signature(String str, String secret) {
    String dest = "";
    if (str!=null) {
      Pattern p = Pattern.compile("\\s*|\t|\r|\n");
      Matcher m = p.matcher(str);
      dest = m.replaceAll("");
    }
    // String ss = Base64.getEncoder().encodeToString(HMAC.Encrypt(secret, dest));
    String ss = HMAC.bytes2Hex(HMAC.Encrypt(secret, dest));
    return ss;
  }

  public static String trim(String str) {
    String dest = "";
    if (str!=null) {
      Pattern p = Pattern.compile("\\s*|\t|\r|\n");
      Matcher m = p.matcher(str);
      dest = m.replaceAll("");
    }
    return dest;
  }
}
