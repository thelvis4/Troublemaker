//
//  IssueLog.swift
//  Troublemaker
//
//  Created by Andrei Raifura on 11/22/15.
//  Copyright © 2015 Andrei Raifura. All rights reserved.
//

typealias IssueLog = String
typealias IssueLogLocation = (filePath: String, line: UInt?, column: UInt?)
typealias IssueLogData = (title: String, issueTypeString: String, location: IssueLogLocation?)

enum IssueLogIdentifier: String {
    case warning = "warning"
    case error = "error"
}

let warning = IssueLogIdentifier.warning.rawValue
let error = IssueLogIdentifier.error.rawValue


internal extension IssueLog {
    
    private var components: [String] {
        get { return self.componentsSeparatedByString(": ") }
    }
    
    internal var issueType: String? {
        get { return getIssueType() }
    }
    
    internal func isValid() -> Bool {
        return components.count > 1 && components.count < 4 && issueType != nil
    }
    
    internal func convert() -> (title: String, issueTypeString: String, location: IssueLogLocation?)? {
        guard self.isValid() else { return nil }
        let title = components.last!
        let type = issueType!
        
        let locationArray = components.remove(title).remove(type)
        let location = locationArray.flatMap { $0.convertToLocation() }
        
        return (title, type, location.first ?? nil)
    }
    
    private func getIssueType() -> String? {
        let lowercasedComponents = self.components.map { $0.lowercaseString }
        if lowercasedComponents.contains(warning) { return warning }
        if lowercasedComponents.contains(error) { return error }
        
        return nil
    }
    
}


private extension String {
    
    private func convertToLocation() -> IssueLogLocation {
        let pattern = ":[0-9]+"
        let matches = self.getMatches(pattern)
        guard let lineResult = matches.first else {
            // No line or column number
            return (self, nil, nil)
        }
        
        let lineStringRange = lineResult.range
        let filePath = self.substringToIndex(self.startIndex.advancedBy(lineStringRange.location))
        let numbers = getNumbersForMatches(matches)
        
        return (filePath, numbers.line, numbers.column)
    }
    
    private func getNumbersForMatches(matches: [NSTextCheckingResult]) -> (line: UInt?, column: UInt?) {
        let numbers = matches.map {
            
            // Transforms into strings. Ex. [":12",":22"]
            self.substringWithNSRange($0.range)
            
            }.map {
                
                // Removes ":" in fron of numbers
                $0.stringByRemovingFirstCharacter()
                
            }.flatMap { UInt($0) }
        
        return (numbers.first, numbers.second)
    }
    
}


internal extension Array where Element : Equatable {
    
    internal func remove(element: Element) -> Array {
        return self.filter { $0 != element }
    }
    
}


internal extension Array {
    
    internal var second: Element? {
        get {
            if self.count < 2 { return nil }
            return self[1]
        }
    }
    
}


private extension String {
    
    private func getMatches(pattern: String) -> [NSTextCheckingResult] {
        do {
            let regex = try NSRegularExpression(pattern: pattern, options: NSRegularExpressionOptions.CaseInsensitive)
            return regex.matchesInString(self, options: [], range: NSMakeRange(0, self.characters.count))
        } catch _ { print("Bad Regex pattern!") }
        
        return []
    }
    
    private func substringWithNSRange(range: NSRange) -> String {
        return (self as NSString).substringWithRange(range)
    }
    
    private func stringByRemovingFirstCharacter() -> String {
        return self.substringFromIndex(self.startIndex.successor())
    }
}
