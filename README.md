# **Project Title:** # 
A Bangla Parts-Of-Speech (POS) tagging software

# **Project Description:** #
The Bangla Parts of Speech tagging tool will take a Bangla text as
input, analyze the text and label each part according to the role it plays in a sentence
(according to morphology, syntax and semantics). The labels include nouns, verbs,
adjectives and so on. For example, it will tag each word of the sentence, “আমি ভাত খাই”
as আমি_PRO ভাত_NN খাই_VRB, where PRO, NN and VRB are standard short forms for
Pronoun, Noun and Verb, respectively.

 Since Parts of speech forms the core of a language, 
this tool can help to understand the basics of Bangla language. This tool can also help in the use and analysis of corpora,
Named Entity Recognition (NER), sentiment analysis, question answering, and word sense disambiguation.

I have used the algorithm proposed by Md. Nesarul Hoque and Md. Hanif Seddiqui, “[Bangla
Parts-of-Speech Tagging using Bangla Stemmer and Rule based Analyzer](https://ieeexplore.ieee.org/document/7488111)”, in 18th
International Conference on Computer and Information Technology (ICCIT), 2015.

I have used C++ as the programming language.

# **Project Outcome:** #
The tool takes a text file as input, uses the algorithm to tag each word with PoS and then writes the outcome on another
text file as shown below :  
<img src="https://user-images.githubusercontent.com/64961018/187032203-f0cf212e-0bc8-4cb4-8e74-9b7398dcf2b7.png" width="500px"></img> <img src="https://user-images.githubusercontent.com/64961018/187032312-970cc6e7-073a-4fff-b195-3ddf3b548bde.png" length="10%" width="200px"></img> 

# **Accuracy:** #
Testing on 782 words collected from [Prothom Alo Online](https://www.prothomalo.com/) yielded 64% accurate result. I have tested the accuracy
using a confusion matrix :   
![image](https://user-images.githubusercontent.com/64961018/187033471-c1c563bd-bfba-4352-b759-a1bdb4f5ffa3.png)  
It is also worthwhile to mention that, it was very hard to find authentic data against which the data produced by the tool could be checked.
So the former was created with the help of volunteers, but the accuracy of that data itself remains dubious.

# **Project Dependency:** #
No platform dependent library was use. So the project runs on any platform. But on windows, it sometimes produces totally wrong outputs for reason(s) unknown.
