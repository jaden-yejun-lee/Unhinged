# Unhinged
The NachenSmall Software Corporation, which has traditionally only built software for running
senior-citizen bingo games, has decided to pivot into a new area. They’ve decided to disrupt the
online matchmaking market and build a new dating app called… Unhinged.

The evil co-CEOs, Carey and David have become increasingly frustrated with today’s superficial,
picture-filled dating apps and have decided to create a text-only dating app to help people focus
on what’s really most important—compatibility. They want their app to have these basic
features:
  ● It must be able to support up to 100k members
  ● Each member can have dozens of attribute-value pairs! For example, for the pairs 
    "hobby" -> "nose hair braiding" and "occupation" -> "pet stylist", "hobby" would be an 
    attribute, and "nose hair braiding" would be its corresponding value, etc.
  ● To identify compatible members, the Unhinged app needs to have a way to translate a 
    member's attribute-value pairs to a set of compatible attribute-value pairs. For example, 
    if a member searching for dates has an attribute-value pair of "hobby" -> "nose hair
    braiding", then this might be translated to a compatible attribute-value pair of "physical
    attribute" -> "long nose hair", since they'd likely want someone who has long nose hair as 
    a partner.
  ● The ability to rank order all potential matches for a member by identifying the people with
    the most compatible attribute-value pairs to that member.
    
Your job is to create 5 classes: 
- Class #1: You need to build a class called PersonProfile that holds a person’s profile (i.e., their
  name, email, and attributes).
- Class #2: You need to build a class called MemberDatabase that can store at least 100k
  person profiles and lets you obtain a profile based on a member’s email address, as well as
  search for the set of members that have a particular attribute-value pair in their profile.
- Class #3: You need to build a class called AttributeTranslator that can translate from an input
  attribute to a set of compatible attributes.
- Class #4: You need to build a class called MatchMaker that can find all relevant matches for a
  given member based on their attribute-value pairs, the attribute-value pairs of the other
  members, and a threshold indicating the minimum set of matching attributes.
- Class #5: You need to build a class template called RadixTree that implements a radix tree-
  based map, capable of mapping std::strings to any data type. 
