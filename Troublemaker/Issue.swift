//
//  Issue.swift
//  Troublemaker
//
//  Created by Andrei Raifura on 11/22/15.
//  Copyright © 2015 Andrei Raifura. All rights reserved.
//

/**
Defines an Issue type to be shown in Xcode.

It takes an instance of `IssueData` as associated value.

An `Issue` can be initialized by calling:
```
let issueData = IssueData(title: "Issue message here")
let issue = Issue.Warning(issueData)
```
or

```
let issue = Issue(log: "warning: A warning here")
```
*/
public enum Issue {
    /**
     Defines a warning. It is usually represented in Xcode as a yellow triangle.
     */
    case Warning(IssueData)
    /**
     Defines a error. It is usually represented in Xcode as a red circle.
     
     */
    case Error(IssueData)
    
    /**
     Returns the associated value.
     
     - returns: An instance of `IssueData` representing the associated value.
     */
    public var data: IssueData {
        switch self {
        case .Warning(let data):
            return data
        case .Error(let data):
            return data
        }
    }
    
}

/**
 
 */
public extension Issue {
    /**
     Initializes an Issue with a log.
     A log can be of any format Xcode supports when it is printed from shell
     script in `Build Phases`.
     
     Some examples of valid logs:
     
     ```
     "warning: A warning message here"
     "error: An error message here"
     "/path/to/file.swift: warning: Warning in file.swift"
     "/path/to/file.swift:32: warning: Warning in file.swift at line 32"
     "/path/to/file.swift:32:4: warning: Warning in file.swift at line 32, column 4"
     ```
     - parameter log: A valid warning or error log.
     
     - returns: An Issue containing data gathered from the log. It fails if an
     invalid log format is given.
     */
    public init?(log: String) {
        guard let data = log.convert() else { return nil }
        let issueData = IssueData(logData: data)
        self = data.issueTypeString == warning ? Warning(issueData) : Error(issueData)
    }
    
}


extension Issue : Equatable {}

public func ==(lhs: Issue, rhs: Issue) -> Bool {
    switch (lhs, rhs) {
    case (let .Warning(lhsData), let .Warning(rhsData)):
        return lhsData == rhsData
    case (let .Error(lhsData), let .Error(rhsData)):
        return lhsData == rhsData
    default:
        return false
    }
    
}
