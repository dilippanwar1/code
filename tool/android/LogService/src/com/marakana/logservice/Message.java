package com.marakana.logservice;

import android.os.Parcel;
import android.os.Parcelable;

/**
 * Message class used to transmit, parcelable is like serializable 
 */
public class Message implements Parcelable {
	private String tag;
	private String text;

	public Message(Parcel in) {
		tag = in.readString();
		text = in.readString();
	}

	public void writeToParcel(Parcel out, int flags) { 
		out.writeString(tag);	// the order should match constructor
		out.writeString(text);
	}

	public int describeContents() {
		return 0;
	}

	public static final Parcelable.Creator<Message> CREATOR = 
			new Parcelable.Creator<Message>() { // must have a creator
		public Message createFromParcel(Parcel source) {
			return new Message(source);
		}

		public Message[] newArray(int size) {
			return new Message[size];
		}
	};

	// Setters and Getters
	public String getTag() {
		return tag;
	}

	public void setTag(String tag) {
		this.tag = tag;
	}

	public String getText() {
		return text;
	}

	public void setText(String text) {
		this.text = text;
	}
}