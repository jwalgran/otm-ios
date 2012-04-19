//
//  OTMDetailCellRenderer.h
//  OpenTreeMap
//
//  Created by Adam Hinz on 4/18/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "OTMDetailTableViewCell.h"

#define OTMDefaultDetailRenderer OTMLabelDetailCellRenderer

@class OTMEditDetailCellRenderer;

/**
 * Generic interface for rendering cells
 * Note that the OTMEditDetailCellRender is responsible
 * for handling edit mode
 */ 
@interface OTMDetailCellRenderer : NSObject

/**
 * Use the given dict as the bases for the cell renderer
 */
+(OTMDetailCellRenderer *)cellRendererFromDict:(NSDictionary *)dict;

/**
 * Key to access data for this cell
 *
 * Examples: 
 *  tree.dbh (tree diameter)
 *  id       (plot id)
 */
@property (nonatomic,strong) NSString *dataKey;

/**
 * Block that takes a single argument (the renderer)
 * and returns a UITableViewCell
 *
 * Default returns table cell with "default" cell styling
 */
@property (nonatomic,strong) Function1 newCellBlock;

/**
 * If this is <nil> then this cell is readonly
 * if this is non-nil the renderer returned will be
 */
@property (nonatomic,strong) OTMEditDetailCellRenderer *editCellRenderer;

// Table View Delegate methods
@property (nonatomic,strong) Function1v clickCallback;

/**
 * Initialize with dictionary structure
 */
-(id)initWithDict:(NSDictionary *)dict;

/**
 * Given a tableView create a new cell (or reuse an old one), prepare
 * it with the given data and this cells rending info and return it
 */
ABSTRACT_METHOD
-(UITableViewCell *)prepareCell:(NSDictionary *)data inTable:(UITableView *)tableView;

@end

/**
 * Render cells for editing
 */
@interface OTMEditDetailCellRenderer : OTMDetailCellRenderer

ABSTRACT_METHOD
-(NSDictionary *)updateDictWithValueFromCell:(NSDictionary *)dict;
@end

/**
 * Render a simple label
 */
@interface OTMLabelDetailCellRenderer : OTMDetailCellRenderer

@property (nonatomic,strong) NSString *label;
@property (nonatomic,strong) NSString *formatStr;

@end

@interface OTMLabelEditDetailCellRenderer : OTMEditDetailCellRenderer<OTMDetailTableViewCellDelegate>

@property (nonatomic,strong) NSString *label;
@property (nonatomic,strong) NSString *updatedString;

@end

/**
 * Shows a static cell that allows a click event
 * (Such as for selecting species)
 *
 * When the user clicks on the cell "callback"
 * is invoked. When editing is finished the value
 * (if non-nil) from data is used as the edited value
 */
@interface OTMStaticClickCellRenderer : OTMEditDetailCellRenderer

-(id)initWithName:(NSString *)aName key:(NSString *)key clickCallback:(Function1v)aCallback;

-(id)initWithKey:(NSString *)key clickCallback:(Function1v)aCallback;

@property (nonatomic,strong) NSString *defaultName;
@property (nonatomic,strong) NSString *name;
@property (nonatomic,strong) id data;

@end
